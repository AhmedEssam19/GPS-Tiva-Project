import sys
import gmplot


def main(coordinates_file):
    latitude_list, longitude_list = [], []
    with open(coordinates_file, mode='rt') as file:
        for line in file:
            coordinate = line.split(',')

            latitude = float(coordinate[3][:2]) + float(coordinate[3][2:]) / 60
            latitude_list.append(latitude)

            longitude = float(coordinate[5][1:3]) + float(coordinate[5][3:]) / 60
            longitude_list.append(longitude)

    api_key = "AIzaSyBpy30mAOa5w-59iSASj-7Fht_zpIoO5uc"
    gmap = gmplot.GoogleMapPlotter.from_geocode("Cairo, Egypt", apikey=api_key)
    gmap.scatter(latitude_list, longitude_list, '#FF0000', size=0.4, marker=False)
    gmap.plot(latitude_list, longitude_list, 'cornflowerblue', edge_width=2.5)
    gmap.draw('map.html')


if __name__ == "__main__":
    main(sys.argv[1])

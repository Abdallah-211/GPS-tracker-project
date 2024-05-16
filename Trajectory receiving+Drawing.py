import folium  # For creating maps
import os      # For opening HTML file automatically
import serial  # For UART communication
import time    # For creating delays
import re      # For cleaning input data

def transmit_letter_via_COM(port, letter):
    try:
        uart = serial.Serial(port, 9600, timeout=1)  # Open the serial port
        if uart.is_open:
            print(f"Serial port {uart.name} successfully opened.")
            uart.write(letter.encode())  # Send letter
            print(f"Sent letter '{letter}' to {uart.name}")
            uart.close()  # Close port
            print(f"Serial port {uart.name} closed.")
        else:
            print(f"Failed to open serial port {uart.name}")
    except serial.SerialException as error:
        print(f"Serial error: {error}")


def split_string_to_coords(data):
    cleaned_data = re.sub(r'[^\d.,-]', '', data)  # Remove non-numeric characters except ',' and '.'
    coordinate_strings = cleaned_data.split(',')  # Split string into individual float strings

    # Convert strings to floats:
    coordinates = [float(value) for value in coordinate_strings if value]  # Ensure no empty strings
    midpoint = len(coordinates) // 2
    latitudes = coordinates[:midpoint]  # First half for latitudes
    longitudes = coordinates[midpoint:]  # Second half for longitudes
    latitudes = [lat for lat in latitudes if lat != 0]  # Remove zero elements
    longitudes = [lon for lon in longitudes if lon != 0]  # Remove zero elements
    return latitudes, longitudes

def generate_map(latitudes, longitudes):
    # Initialize map
    map_instance = folium.Map(location=[latitudes[0], longitudes[0]], zoom_start=15, tiles='OpenStreetMap')

    # List of location coordinates
    coords = list(zip(latitudes, longitudes))
    # Mark start and end points
    folium.Marker(coords[0], tooltip="Start", icon=folium.Icon(color="blue", icon="map-marker")).add_to(map_instance)
    folium.Marker(coords[-1], tooltip="End", icon=folium.Icon(color="red", icon="map-marker")).add_to(map_instance)
    folium.PolyLine(coords, color="blue", weight=2.5, opacity=1).add_to(map_instance)  # Draw path

    html_path = "mapped_locations.html" #Save the map to an HTML file
    map_instance.save(html_path)   
    os.system(html_path)                #Automatically opening the HTML file

def read_and_plot(port_name, baud):
    try:
        uart_connection = serial.Serial(port_name, baud)  # Open serial port
        print("Serial port successfully opened.")

        data_string = uart_connection.readline().decode('utf-8').strip()  # Read data from serial port
        latitudes, longitudes = split_string_to_coords(data_string)  # Convert string to coordinate arrays
        print("Latitudes:", latitudes)
        print("Longitudes:", longitudes)
        generate_map(latitudes, longitudes)  # Plot coordinates on map
    except serial.SerialException as error:
        print("Serial error:", error)
    except KeyboardInterrupt:
        print("Process interrupted. Exiting...")
    finally:
        if uart_connection and uart_connection.is_open:
            uart_connection.close()

def main():
    transmit_letter_via_COM('COM6', 'U')  # Transmit letter to receive data
    read_and_plot('COM6', 9600)  # Read and plot received data

if __name__ == "__main__":
    main()

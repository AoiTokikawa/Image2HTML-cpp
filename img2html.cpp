#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "CImg.h" //using the CImg library

std::string to_hex(unsigned char c) { //converts unsigned char to hex string
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    return ss.str();
}

std::string hex2HTML(const std::string& hex_str) { //uses the hex string and creates HTML
	return "<span style=\"display:inline-block;width:1px;height:1px;background-color:#" + hex_str + "\"></span>";
}

bool write2file(std::ofstream& file, const std::string& data) { //this function writes to the file and returns a bool based on success
    file << data;  // Attempt to write data to the file
    if (file.fail()) {  // Check if the write operation failed
        std::cerr << "Error writing to the file." << std::endl;
        return false;  // Indicate failure
    }
    return true;  // Indicate success
}

bool valid_hex_color (const std::string& hex_color) { //ensures that the hex string is in rrggbb or rrggbbaa format
	if (hex_color.length() != 6 && hex_color.length() != 8) {
		return false;
	}
	
	return std::all_of(hex_color.begin(), hex_color.end(), [](unsigned char c) { 
			return std::isxdigit(c); 
		});
}

int main(int argc, char *argv[]) {
	
	if (argc < 5) { //check if the correct parameters are being used
		std::cerr << "Usage: " << argv[0] << " [image filename] [html output filename] [html document background-color] [image-alignment]\n";
		std::cerr << "\t[image filename] - Name of Image being processed\n";
		std::cerr << "\t[html output filename] - Name of html output file\n";
		std::cerr << "\t[html document background-color] - Background color of HTML document (only lowercase rrggbb or rrggbbaa hex codes allowed)\n";
		std::cerr << "\t[image-alignment] - Image Alignment (only 'center', 'left', or 'right' allowed)\n";
		return 3;
	}
	
	std::string bg_color = argv[3];
	
	std::string alignment = argv[4];
	
	if (!valid_hex_color(bg_color)) {
		std::cerr << "Only lowercase rrggbb or rrggbbaa hex codes allowed\n";
		return 3;
	} 
	
	if (alignment != "center" && alignment != "right" && alignment != "left") {
		std::cerr << "Only 'center', 'right', or 'left' accepted for the [image-alignment] argument\n";
		return 3;
	}
	
	std::ofstream html_file(argv[2]);
	
	if (!html_file.is_open()) {
		std::cerr << "Could not open file for writing\n";
		return 1;
	}
	
	
	
	std::string html_start = "<!DOCTYPE html><html><head></head><body style='background-color:#" + bg_color + ";'><pre style='font-size:0;margin:0;padding:0;line-height:0;text-align:" + alignment +  ";'>";
	
	if (!write2file(html_file, html_start)) {
		std::cerr << "Failed to write to file\n";
		return 2;
	}
	
	cimg_library::CImg<unsigned char> image(argv[1]);
	int width = image.width();
    	int height = image.height();
    	int channels = image.spectrum();

	if (image.is_empty()) {
		std::cerr << "Could not read image: " << argv[1] << std::endl;
		return -1;
	}

	// Accessing pixel data
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			unsigned char red = image(x, y, 0, 0);
			unsigned char green = image(x, y, 0, 1);
			unsigned char blue = image(x, y, 0, 2);
			unsigned char alpha = (channels == 4) ? image(x,y, 0, 3) : 255;
			std::string full_hex = to_hex(red) + to_hex(green) + to_hex(blue) + to_hex(alpha);
			std::string c_html = hex2HTML(full_hex);
			
			if (!write2file(html_file, c_html)) {
				std::cerr << "Failed to write to file\n";
				return 2;
			}

			if (x + 1 == width) {
				if (!write2file(html_file, "\n")) {
					std::cerr << "Failed to write to file\n";
					return 2;
				}
			}
		}
	}
	
	if (!write2file(html_file, "</pre></body></html>")) {
		std::cerr << "Failed to write to file\n";
		return 2;
	}
	
	html_file.close();

	return 0;

}

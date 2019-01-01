#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>  // Video write
#include <string>
#include <dirent.h>

int main()
{
	DIR *dir;
	struct dirent *ent;
	cv::VideoWriter outputVideo;
	cv::Mat frame;
	std::string path = "../data/right/";
	std::vector<std::string> file_list;

	cv::Size S = cv::Size(1242, 375); // cv::Size((int) frame.cols, (int) frame.rows);
	std::cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height << std::endl;

	int codec = cv::VideoWriter::fourcc('a', 'v', 'c', '1'); // select desired codec (must be available at runtime)
	outputVideo.open("output.mp4", codec, 24, S, true);
	if (!outputVideo.isOpened())
	{
		std::cout  << "Could not open the output video for write: " << std::endl;
		return -1;
	}

	if ((dir = opendir (path.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 ) {
				std::string file_path = path.c_str() + std::string(ent->d_name);
				file_list.push_back( file_path );
			}
		}
		closedir (dir);
	} else {
		/* could not open directory */
		perror ("");
		return EXIT_FAILURE;
	}
	std::sort(file_list.begin(), file_list.end());

	while(!file_list.empty()) {
		std::string current_file = file_list.front();
		file_list.erase(file_list.begin());
		std::cout << current_file << std::endl;
		frame = cv::imread(current_file, cv::IMREAD_UNCHANGED);
		imshow("Live", frame);
		outputVideo.write(frame);
	}
	outputVideo.release();

	return 0;
}

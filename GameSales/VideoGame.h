#pragma once
#include <string>
using namespace std;

class VideoGame
{
private:
	int rank;
	string name;
	string platform;
	int year;
	string genre;
	string publisher;
	float NA_sales;
	float EU_sales;
	float JP_sales;
	float other_sales;
	float global_sales;


public:
	VideoGame();
	VideoGame(string name, string publisher, int year, float global_sales);
	VideoGame(string name, string platform, float global_sales);
	VideoGame(int rank, string name, string platform, int year, string genre, string publisher, float NA_sales, float EU_sales, float JP_sales, float other_sales, float global_sales);

	int get_rank();

	void set_name(string name);
	string get_name();

	void set_platform(string platform);
	string get_platform();

	void set_year(int year);
	int get_year();

	void set_genre(string genre);
	string get_genre();

	void set_publisher(string publisher);
	string get_publisher();

	void set_NA_sales(float NA_sales);
	float get_NA_sales();
	
	void set_EU_sales(float EU_sales);
	float get_EU_sales();

	void set_JP_sales(float JP_sales);
	float get_JP_sales();

	void set_other_sales(float other_sales);
	float get_other_sales();

	void set_global_sales(float global_sales);
	float get_global_sales();

	string to_string();
	string top_EU_to_string();
	string list_to_string();

};


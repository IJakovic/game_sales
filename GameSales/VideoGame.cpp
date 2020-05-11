#include "VideoGame.h"
#include <sstream>

VideoGame::VideoGame()
{
}

VideoGame::VideoGame(string name, string publisher, int year, float global_sales)
{
	this->name = name;
	this->publisher = publisher;
	this->year = year;
	this->global_sales = global_sales;
}

VideoGame::VideoGame(string name, string platform, float global_sales)
{
	this->name = name;
	this->platform = platform;
	this->global_sales = global_sales;
}

VideoGame::VideoGame(int rank, string name, string platform, int year, string genre, string publisher, float NA_sales, float EU_sales, float JP_sales, float other_sales, float global_sales)
{
	this->rank = rank;
	this->name = name;
	this->platform = platform;
	this->year = year;
	this->genre = genre;
	this->publisher = publisher;
	this->NA_sales = NA_sales;
	this->EU_sales = EU_sales;
	this->JP_sales = JP_sales;
	this->other_sales = other_sales;
	this->global_sales = global_sales;
}

int VideoGame::get_rank()
{
	return rank;
}

void VideoGame::set_name(string name)
{
	this->name = name;
}

string VideoGame::get_name()
{
	return name;
}

void VideoGame::set_platform(string platform)
{
	this->platform = platform;
}

string VideoGame::get_platform()
{
	return platform;
}

void VideoGame::set_year(int year)
{
	this->year = year;
}

int VideoGame::get_year()
{
	return year;
}

void VideoGame::set_genre(string genre)
{
	this->genre = genre;
}

string VideoGame::get_genre()
{
	return genre;
}

void VideoGame::set_publisher(string publisher)
{
	this->publisher = publisher;
}

string VideoGame::get_publisher()
{
	return publisher;
}

void VideoGame::set_NA_sales(float NA_sales)
{
	this->NA_sales = NA_sales;
	global_sales += NA_sales;
}

float VideoGame::get_NA_sales()
{
	return NA_sales;
}

void VideoGame::set_EU_sales(float EU_sales)
{
	this->EU_sales = EU_sales;
	global_sales += EU_sales;
}

float VideoGame::get_EU_sales()
{
	return EU_sales;
}

void VideoGame::set_JP_sales(float JP_sales)
{
	this->JP_sales = JP_sales;
	global_sales += JP_sales;
}

float VideoGame::get_JP_sales()
{
	return JP_sales;
}

void VideoGame::set_other_sales(float other_sales)
{
	this->other_sales = other_sales;
	global_sales += other_sales;
}

float VideoGame::get_other_sales()
{
	return other_sales;
}

void VideoGame::set_global_sales(float global_sales)
{
	this->global_sales = global_sales;
}

float VideoGame::get_global_sales()
{
	return global_sales;
}

string VideoGame::to_string()
{
	stringstream ss;
	ss << name << ", " << publisher << ", " << year << ", " << global_sales;
	return ss.str();
}

string VideoGame::top_EU_to_string()
{
	stringstream ss;
	ss << name << ": " << EU_sales << ",00 USD";
	return ss.str();
}

string VideoGame::list_to_string()
{
	stringstream ss;
	ss << name << ',' << platform << ',' << global_sales;
	return ss.str();
}



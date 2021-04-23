/*
Author:   Ilina Elena (ferr.98@mail.ru)
*/
#ifndef __WEATHER_H__
#define __WEATHER_H__

#include <wx/progdlg.h>

#include "vector2D.h"
#include "ocpndc.h"

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <fstream>
#include <regex>

#include <curl/curl.h>

class HyperlinkList;
class ChartCanvas;
class ViewPort;
class ocpnDCl;
class LLBBox;

class Weather
{
public:

	struct PointWeatherData {

		std::string creation_time;//replace
		std::string time;
		double latitude;
		double longitude;
		double wind_u;
		double wind_v;
		double wave_height;
		double wave_wind_length;
		double wave_wind_period;
		double wave_direction;
		double ripple_height;
		double ripple_direction;

		PointWeatherData() {}

		PointWeatherData(const std::string &creationTime, const std::string &time, double latitude, double longitude,
			double windU, double windV, double waveHeight, double waveWindLength, double waveWindPeriod,
			double waveDirection, double rippleHeight, double rippleDirection) : creation_time(creationTime),
			time(time),
			latitude(latitude),
			longitude(longitude),
			wind_u(windU), wind_v(windV),
			wave_height(waveHeight),
			wave_wind_length(
				waveWindLength),
			wave_wind_period(
				waveWindPeriod),
			wave_direction(waveDirection),
			ripple_height(rippleHeight),
			ripple_direction(
				rippleDirection) {}


	};

	Weather();
	virtual ~Weather();

	void Draw(ChartCanvas *cc, ocpnDC& dc, ViewPort &VP, const LLBBox &box);

private:
	double do_work(const std::string& str);
	void draw_gradient(ChartCanvas *cc, ocpnDC& dc, ViewPort &VP, const LLBBox &box);
	std::vector<PointWeatherData> get_all_weather_data(const std::string& path);
	double find_max_wave_height();
	double find_min_wave_height();
	double find_max_ripple_height();
	double find_min_ripple_height();

	static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
	static bool download_weather_from_esimo();

private:
	 bool is_downloaded = false;
	 std::vector<PointWeatherData> data;


	 bool draw_downloaded = false;
};
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Attendance
{
// define
public:
	enum Day
	{
		Monday = 0,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday, 
		DaysCount
	};

	static const string GOLD_GRADE = "GOLD";
	static const string SILVER_GRADE = "SILVER";
	static const string NORMAL_GRADE = "NORMAL";
	static const int SPECIAL_DAY_POINT = 10;
	static const int START_MEMBER_ID = 1;
	static const int MAX_MEMBER_ID = 19;
	static const int MEMBERS_COUNT = MAX_MEMBER_ID + 1;
	static const int WEIGHTED_VALUE_PER_DAY[DaysCount] = { 1, 1, 3, 1, 1, 2, 2 };

// member variables
private:
	map<string, int> id_map;
	int id_cnt = 0;

	//dat[사용자ID][요일]
	int attended_days[MEMBERS_COUNT][DaysCount];
	int points[MEMBERS_COUNT];
	string grade[MEMBERS_COUNT];


	string names[MEMBERS_COUNT];

	int wednesday_attendance[MEMBERS_COUNT];
	int weekend_attendance[MEMBERS_COUNT];

// member functions
private:
	int getMemberId(string member_name) {
		if (id_map.count(member_name) == 0) {
			id_map.insert({ member_name, ++id_cnt });
			names[id_cnt] = member_name;
		}
		return id_map[member_name];
	}

	void updateAttendance(int member_id, string week_day)
	{
		int day = 0;
		if (week_day == "monday") {
			day = Monday;
		}
		if (week_day == "tuesday") {
			day = Tuesday;
		}
		if (week_day == "wednesday") {
			day = Wednesday;
			wednesday_attendance[member_id] += 1;
		}
		if (week_day == "thursday") {
			day = Thursday;
		}
		if (week_day == "friday") {
			day = Friday;
		}
		if (week_day == "saturday") {
			day = Saturday;
			weekend_attendance[member_id] += 1;
		}
		if (week_day == "sunday") {
			day = Sunday;
			weekend_attendance[member_id] += 1;
		}

		attended_days[member_id][day] += 1;
	}

	void updateMemberPoint(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			for (int day = Monday; day < DaysCount; day++)
			{
				points[member_id] += attended_days[member_id][day] * WEIGHTED_VALUE_PER_DAY[day];
			}
		}
	}

	void updateSpecialDayPoint(void)
	{
		static const int SPECIAL_POINT_CRITERIA = 9;

		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			if (wednesday_attendance[member_id] > SPECIAL_POINT_CRITERIA) {
				points[member_id] += SPECIAL_DAY_POINT;
			}

			if (weekend_attendance[member_id] > SPECIAL_POINT_CRITERIA) {
				points[member_id] += SPECIAL_DAY_POINT;
			}
		}
	}

	void updateGrade(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			if (points[member_id] >= 50) {
				grade[member_id] = GOLD_GRADE;
			}
			else if (points[member_id] >= 30) {
				grade[member_id] = SILVER_GRADE;
			}
			else {
				grade[member_id] = NORMAL_GRADE;
			}
		}
	}

	bool haveAttenedOnSpecialDay(int member_id)
	{
		return ((wednesday_attendance[member_id] != 0) || (weekend_attendance[member_id] != 0));
	}
public :
	void printMembersPointAndGrade(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			cout << "NAME : " << names[member_id] << ", ";
			cout << "POINT : " << points[member_id] << ", ";
			cout << "GRADE : " << grade[member_id] << "\n";
		}
	}

	void printRemovedMember(void)
	{
		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";

		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {

			if ((grade[member_id] == NORMAL_GRADE) && (haveAttenedOnSpecialDay(member_id) == false)) {
				std::cout << names[member_id] << "\n";
			}
		}
	}

	void UpdateInitialMemberAttendanceInfo() {
		ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

		for (int i = 0; i < 500; i++) {
			string member_name, week_day;
			fin >> member_name >> week_day;

			updateAttendance(getMemberId(member_name), week_day);		
		}
	}
};
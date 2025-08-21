#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class AttendedDays
{
private:
	static const int DAYS = 7;
	int attended_day_count[DAYS];

public:
	void updateAttendedDays(int day)
	{
		attended_day_count[day]++;
	}

	int getAttenedCount(int day)
	{
		return attended_day_count[day];
	}

	int getWeekendCount(void)
	{
		static const int SATURDAY = 5;
		static const int SUNDAY = 6;
		return (attended_day_count[SATURDAY] + attended_day_count[SUNDAY]);
	}
};

class Grade
{
private:
	string grade_status;
	int grade_criteria;
public:
	Grade(string _grade_status, int _grade_criteria)
		: grade_status(_grade_status),
     	  grade_criteria(_grade_criteria)
	{
		// do nothing;
	}
	string GetGrade()
	{
		return grade_status;
	}

	void Update(string _grade_status)
	{
		grade_status = _grade_status;
	}

	int getCriteria(void)
	{
		return grade_criteria;
	}
};

class GoldGrade: public Grade
{
public:
	GoldGrade()
		:Grade("GOLD", 50)
	{
		// do nothing
	}
};

class SilverGrade: public Grade
{
public:
	SilverGrade()
		:Grade("SILVER", 30)
	{
		// do nothing
	}
};

class NormalGrade: public Grade
{
public:
	NormalGrade()
		:Grade("NORMAL", 0)
	{
		// do nothing
	}
};

class Member
{
private:
	Grade *current_grade;
	AttendedDays attened_days;
	string name;
	int points;

public:
	void updateName(string _name)
	{
		name = _name;
	}

	string getName()
	{
		return name;
	}

	string getGrade()
	{
		return current_grade->GetGrade();
	}

	void setGrade(Grade *grade)
	{
		current_grade = grade;
	}

	void updateAttendCount(int day)
	{
		attened_days.updateAttendedDays(day);
	}

	int getAttenedCount(int day)
	{
		return attened_days.getAttenedCount(day);
	}

	AttendedDays* getAttendDays()
	{
		return &attened_days;
	}

	void updatePoints(int _points)
	{
		points += _points;
	}

	int getPoints(void)
	{
		return points;
	}

	void printInfo()
	{
		cout << "NAME : " << name << ", ";
		cout << "POINT : " << points << ", ";
		cout << "GRADE : " << current_grade->GetGrade() << ", ";
		cout << "\n";
	}
};

class PointCalculator
{
private:

	static const int SPECIAL_DAY_POINT = 10;
	static const int SPECIAL_POINT_CRITERIA = 9;
	static const int DAY_COUNT = 7;

	const int WEIGHTED_VALUE_PER_DAY[DAY_COUNT] = { 1, 1, 3, 1, 1, 2, 2 };
	//Day specialDay = Wednesday;

public:
	int getCaculatedPoint(int point, int day)
	{
		return point * WEIGHTED_VALUE_PER_DAY[day];
	}
	void updateSpecialDayCalculatedPoint(Member *member, vector<int> specialDays) {

		for (int specialDay : specialDays)
		{
			if (member->getAttendDays()->getAttenedCount(specialDay) > SPECIAL_POINT_CRITERIA) {
				member->updatePoints(SPECIAL_DAY_POINT);
			}
		}

		if (member->getAttendDays()->getWeekendCount() > SPECIAL_POINT_CRITERIA){
			member->updatePoints(SPECIAL_DAY_POINT);
		}
	}
};





class ExcerciseClubPolicy
{
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
public:
	map<string, int> id_map;
	int id_cnt = 0;

public:
	virtual int getMemberId(string member_name) = 0;

	virtual void updateAttendance(int member_id, string week_day) = 0;

	virtual void updateMemberPoint(void) = 0;

	virtual void updateSpecialDayPoint(void) = 0;

	virtual void updateGrade(void) = 0;

	virtual bool haveAttenedOnSpecialDay(int member_id) = 0;

	virtual void printMembersInfo(void) = 0;

	virtual void printRemovedMember(void) = 0;

	virtual void UpdateInitialMemberAttendanceInfo() = 0;

};

class BaseballClubPolicy : public ExcerciseClubPolicy
{
// define
private:
	const string GOLD_GRADE = "GOLD";
	const string SILVER_GRADE = "SILVER";
	const string NORMAL_GRADE = "NORMAL";

	static const int SPECIAL_DAY_POINT = 10;
	static const int START_MEMBER_ID = 1;
	static const int MAX_MEMBER_ID = 19;
	static const int MEMBERS_COUNT = MAX_MEMBER_ID + 1;

// member variables
public:	
	Member member[MEMBERS_COUNT];
	PointCalculator pointCalculator;

	GoldGrade goldGrade;
	SilverGrade silverGrade;
	NormalGrade normalGrade;

	vector<int> specialDays{ Wednesday };
// member functions
public:
	int getMemberId(string member_name) {
		if (id_map.count(member_name) == 0) {
			id_map.insert({ member_name, ++id_cnt });
			member[id_cnt].updateName(member_name);
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
		}
		if (week_day == "thursday") {
			day = Thursday;
		}
		if (week_day == "friday") {
			day = Friday;
		}
		if (week_day == "saturday") {
			day = Saturday;
		}
		if (week_day == "sunday") {
			day = Sunday;
		}
		member[member_id].updateAttendCount(day);
	}

	void updateMemberPoint(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			for (int day = Monday; day < DaysCount; day++)
			{
				member[member_id].updatePoints(pointCalculator.getCaculatedPoint(member[member_id].getAttenedCount(day), day));
			}
		}
	}

	void updateSpecialDayPoint(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			pointCalculator.updateSpecialDayCalculatedPoint(&member[member_id], specialDays);
		}
	}

	void updateGrade(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			if (member[member_id].getPoints() >= goldGrade.getCriteria()) {
				member[member_id].setGrade(&goldGrade);
			}
			else if (member[member_id].getPoints() >= silverGrade.getCriteria()) {
				member[member_id].setGrade(&silverGrade);
			}
			else {
				member[member_id].setGrade(&normalGrade);
			}
		}
	}

	bool haveAttenedOnSpecialDay(int member_id)
	{
		bool is_attened_on_special_days = false;
		for (int specialDay : specialDays)
		{
			if (member[member_id].getAttenedCount(specialDay) > 0) {
				is_attened_on_special_days = true;
			}
		}

		if (member[member_id].getAttendDays()->getWeekendCount() > 0){
			is_attened_on_special_days = true;
		}
		return is_attened_on_special_days;
	}

	void printMembersInfo(void)
	{
		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {
			member[member_id].printInfo();
		}
	}

	void printRemovedMember(void)
	{
		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";

		for (int member_id = START_MEMBER_ID; member_id <= id_cnt; member_id++) {

			if ((haveAttenedOnSpecialDay(member_id) == false) && (member[member_id].getGrade() == NORMAL_GRADE)) {
				std::cout << member[member_id].getName() << "\n";
			}
		}
	}

	void UpdateInitialMemberAttendanceInfo() {
		ifstream fin{ "C:\\Users\\User\\source\\repos\\Project1\\Project1\\attendance_weekday_500.txt"  }; //500개 데이터 입력

		for (int i = 0; i < 500; i++) {
			string member_name, week_day;
			fin >> member_name >> week_day;
			int member_id = getMemberId(member_name);

			updateAttendance(member_id, week_day);		
		}
	}
};


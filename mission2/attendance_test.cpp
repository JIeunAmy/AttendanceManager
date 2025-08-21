#include "gmock/gmock.h"
#include "attendance.cpp"

#include <iostream>
#include <fstream>

using namespace testing;
using namespace std;
class AttendanceFixture : public Test
{
public:
	Attendance attendance;
};

TEST_F(AttendanceFixture, TC1)
{
	attendance.UpdateInitialMemberAttendanceInfo();
	EXPECT_EQ(attendance.id_cnt, 19);
}

TEST_F(AttendanceFixture, TC2)
{
	attendance.updateAttendance(1, "monday");
	attendance.updateAttendance(1, "tuesday");
	attendance.updateAttendance(1, "wednesday");
	attendance.updateAttendance(1, "thursday");
	attendance.updateAttendance(1, "friday");
	attendance.updateAttendance(1, "saturday");
	attendance.updateAttendance(1, "sunday");

	for (int i = 0 ;i < 7;++i)
	{
		EXPECT_EQ(attendance.attended_days[1][i], 1);
	}

	EXPECT_EQ(attendance.wednesday_attendance[1], 1);
	EXPECT_EQ(attendance.weekend_attendance[1], 2);
}

TEST_F(AttendanceFixture, TC3)
{
	attendance.UpdateInitialMemberAttendanceInfo();

	attendance.updateMemberPoint();
	attendance.updateSpecialDayPoint();
	attendance.updateGrade();

	attendance.printRemovedMember();
	EXPECT_EQ(1, 1);
}


TEST_F(AttendanceFixture, TC4)
{
	attendance.UpdateInitialMemberAttendanceInfo();

	attendance.updateMemberPoint();
	attendance.updateSpecialDayPoint();
	attendance.updateGrade();
	attendance.printMembersPointAndGrade();
}


TEST_F(AttendanceFixture, TC5)
{
	attendance.UpdateInitialMemberAttendanceInfo();

	attendance.updateMemberPoint();
	attendance.updateSpecialDayPoint();
	attendance.updateGrade();

	EXPECT_TRUE(attendance.haveAttenedOnSpecialDay(attendance.getMemberId("Will")));
	EXPECT_FALSE(attendance.haveAttenedOnSpecialDay(attendance.getMemberId("Zane")));	
}

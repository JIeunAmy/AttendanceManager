#include "gmock/gmock.h"
#include "attendance.cpp"

#include <iostream>
#include <fstream>

using namespace testing;
using namespace std;
class AttendanceFixture : public Test
{
public:
	BaseballClubPolicy baseballClubPolicy;
};

TEST_F(AttendanceFixture, TC1)
{
	baseballClubPolicy.UpdateInitialMemberAttendanceInfo();
	EXPECT_EQ(baseballClubPolicy.id_cnt, 19);
}

TEST_F(AttendanceFixture, TC2)
{
	baseballClubPolicy.updateAttendance(1, "monday");
	baseballClubPolicy.updateAttendance(1, "tuesday");
	baseballClubPolicy.updateAttendance(1, "wednesday");
	baseballClubPolicy.updateAttendance(1, "thursday");
	baseballClubPolicy.updateAttendance(1, "friday");
	baseballClubPolicy.updateAttendance(1, "saturday");
	baseballClubPolicy.updateAttendance(1, "sunday");

	for (int i = 0 ;i < 7;++i)
	{
		EXPECT_EQ(baseballClubPolicy.member[1].getAttenedCount(i), 1);
	}
}

TEST_F(AttendanceFixture, TC3)
{
	baseballClubPolicy.UpdateInitialMemberAttendanceInfo();

	baseballClubPolicy.updateMemberPoint();
	baseballClubPolicy.updateSpecialDayPoint();
	baseballClubPolicy.updateGrade();

	baseballClubPolicy.printRemovedMember();
}

TEST_F(AttendanceFixture, TC4)
{
	baseballClubPolicy.UpdateInitialMemberAttendanceInfo();

	baseballClubPolicy.updateMemberPoint();
	baseballClubPolicy.updateSpecialDayPoint();
	baseballClubPolicy.updateGrade();
	baseballClubPolicy.printRemovedMember();

	baseballClubPolicy.printMembersInfo();
}

TEST_F(AttendanceFixture, WED_10)
{
	int member_id = baseballClubPolicy.getMemberId("test");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");
	baseballClubPolicy.updateAttendance(member_id, "wednesday");

	baseballClubPolicy.updateGrade();
	baseballClubPolicy.updateMemberPoint();
	baseballClubPolicy.updateSpecialDayPoint();
	EXPECT_EQ(baseballClubPolicy.member[member_id].getPoints(), 40);	
}

TEST_F(AttendanceFixture, WEEKEND_10)
{
	int member_id = baseballClubPolicy.getMemberId("test");
	baseballClubPolicy.updateAttendance(member_id, "saturday");
	baseballClubPolicy.updateAttendance(member_id, "saturday");
	baseballClubPolicy.updateAttendance(member_id, "saturday");
	baseballClubPolicy.updateAttendance(member_id, "saturday");
	baseballClubPolicy.updateAttendance(member_id, "saturday");
	baseballClubPolicy.updateAttendance(member_id, "sunday");
	baseballClubPolicy.updateAttendance(member_id, "sunday");
	baseballClubPolicy.updateAttendance(member_id, "sunday");
	baseballClubPolicy.updateAttendance(member_id, "sunday");
	baseballClubPolicy.updateAttendance(member_id, "sunday");

	baseballClubPolicy.updateGrade();
	baseballClubPolicy.updateMemberPoint();
	baseballClubPolicy.updateSpecialDayPoint();
	EXPECT_EQ(baseballClubPolicy.member[member_id].getPoints(), 30);
}

TEST_F(AttendanceFixture, TC5)
{
	baseballClubPolicy.UpdateInitialMemberAttendanceInfo();

	baseballClubPolicy.updateMemberPoint();
	baseballClubPolicy.updateSpecialDayPoint();
	baseballClubPolicy.updateGrade();
	baseballClubPolicy.printMembersInfo();

	EXPECT_TRUE(baseballClubPolicy.haveAttenedOnSpecialDay(baseballClubPolicy.getMemberId("Will")));
	EXPECT_FALSE(baseballClubPolicy.haveAttenedOnSpecialDay(baseballClubPolicy.getMemberId("Zane")));
}

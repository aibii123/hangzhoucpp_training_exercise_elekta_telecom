#include<iostream>
#include<gmock/gmock.h>
using namespace std;
#define BaselyMohthRateOfGold 49.95
#define BaselyMohthRateOfSilver 29.95
#define RatePerAdditonalLineOfGold 14.5
#define RatePerAdditonalLineOfSilver 21.5
#define RateOfGoldExceddOneMint 0.45
#define RateOfSilverExceddOneMint 0.54
#define BaselyMohthRateOfGoldIncludeMinutes 1000
#define BaselyMohthRateOfSilverIncludeMinutes 500
#define FamilyDiscoutRateOfLinesMoreThanFour 5
#define TheNumOfDiscoutWhenLinesReached 3

enum PlanType
{
    GOLD,
    SLIVER
};
class customer
{
    public:
        customer(PlanType m_type,int m_numoflines):type(m_type),numoflines(m_numoflines){};
        
        customer(PlanType m_type,int m_numoflines,int m_usedinutes):type(m_type),numoflines(m_numoflines),usedinutes(m_usedinutes){};
        double getmonthlyphonebill(){return monthlyphonebill;}
        double getmonthlyphonebillincludingexceedminutes(){return monthlyphonebillincludingexceedminutes;}
        
       virtual void CalculateMonthlyPhoneBill()
        {
            
            switch(type)
            {
                case GOLD:
                { 
                    if(numoflines<4)
                        monthlyphonebill=BaselyMohthRateOfGold+(numoflines-1)*RatePerAdditonalLineOfGold;
                    else 
                        monthlyphonebill=BaselyMohthRateOfGold+(numoflines-1)*RatePerAdditonalLineOfGold+(numoflines-TheNumOfDiscoutWhenLinesReached)*FamilyDiscoutRateOfLinesMoreThanFour;
                    if(usedinutes>BaselyMohthRateOfGoldIncludeMinutes)
                        monthlyphonebillincludingexceedminutes=monthlyphonebill+RateOfGoldExceddOneMint*(usedinutes-BaselyMohthRateOfGoldIncludeMinutes);
                    else
                        monthlyphonebillincludingexceedminutes=monthlyphonebill;
                    break;
        
                }
                case SLIVER:
                { 
                    if(numoflines<4)
                        monthlyphonebill=BaselyMohthRateOfSilver+(numoflines-1)*RatePerAdditonalLineOfSilver;
                    else 
                    monthlyphonebill=BaselyMohthRateOfGold+(numoflines-1)*RatePerAdditonalLineOfGold+(numoflines-TheNumOfDiscoutWhenLinesReached)*FamilyDiscoutRateOfLinesMoreThanFour;
                    if(usedinutes>BaselyMohthRateOfSilverIncludeMinutes)
                        monthlyphonebillincludingexceedminutes=monthlyphonebill+RateOfSilverExceddOneMint*(usedinutes-RateOfSilverExceddOneMint);
                    else
                        monthlyphonebillincludingexceedminutes=monthlyphonebill;
                    break;
        
                }
        
            }
            cout<<"the monthlyphonebill of  "<<type<<" with"<<numoflines<<"lines is "<<monthlyphonebill<<endl;
        
        }
        
    private:
        PlanType type;
        int numoflines;
        int usedinutes;
        double monthlyphonebill;
        double monthlyphonebillincludingexceedminutes;

        
};
TEST(Electa_telecom,MonthlyPhoneBillTestcases)
{
   customer customer1(GOLD,1);
   customer1.CalculateMonthlyPhoneBill();
   ASSERT_EQ(49.95,customer1.getmonthlyphonebill());
   
   customer customer2(GOLD,2);
   customer2.CalculateMonthlyPhoneBill();
   ASSERT_EQ(64.45,customer2.getmonthlyphonebill());
   
   customer customer3(SLIVER,1);
   customer3.CalculateMonthlyPhoneBill();
   ASSERT_EQ(29.95,customer3.getmonthlyphonebill());
   
   customer customer4(SLIVER,3);
   customer4.CalculateMonthlyPhoneBill();
   ASSERT_EQ(72.95,customer4.getmonthlyphonebill());

   
   customer customer5(SLIVER,4);
   customer5.CalculateMonthlyPhoneBill();
   ASSERT_EQ(77.95,customer5.getmonthlyphonebill());
}
TEST(Electa_telecom,MonthlyPhoneBillIncludingExcessMinutesTestcases)
{
   customer customer1(GOLD,1,999);
   customer1.CalculateMonthlyPhoneBill();
   ASSERT_EQ(49.95,customer1.getmonthlyphonebillincludingexceedminutes());
   
   customer customer2(GOLD,1,1000);
   customer2.CalculateMonthlyPhoneBill();
   ASSERT_EQ(49.95,customer2.getmonthlyphonebillincludingexceedminutes());
   
   customer customer3(GOLD,1,1001);
   customer3.CalculateMonthlyPhoneBill();
   ASSERT_EQ(54.40,customer3.getmonthlyphonebillincludingexceedminutes());
   
   customer customer4(GOLD,1,1010);
   customer4.CalculateMonthlyPhoneBill();
   ASSERT_EQ(54.45,customer4.getmonthlyphonebillincludingexceedminutes());


   customer customer5(SLIVER,1,499);
   customer5.CalculateMonthlyPhoneBill();
   ASSERT_EQ(29.95,customer5.getmonthlyphonebillincludingexceedminutes());
   
   customer customer6(SLIVER,1,500);
   customer6.CalculateMonthlyPhoneBill();
   ASSERT_EQ(29.95,customer6.getmonthlyphonebillincludingexceedminutes());

   
   customer customer7(SLIVER,1,520);
   customer7.CalculateMonthlyPhoneBill();
   ASSERT_EQ(40.72,customer7.getmonthlyphonebillincludingexceedminutes());
}

int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}



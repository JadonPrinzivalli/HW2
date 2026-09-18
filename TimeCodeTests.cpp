#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

void TestComponentsToSeconds()
{
    cout << "Testing ComponentsToSeconds" << endl;

    // Random but safe inputs
    long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
    assert(t == 11862);

    cout << "PASSED!" << endl << endl;
}

void TestDefaultConstructor()
{
    cout << "Testing Default Constructor" << endl;

    TimeCode tc;

    assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestComponentConstructor()
{
    cout << "Testing Component Constructor" << endl;

    TimeCode tc = TimeCode(0, 0, 0);
    assert(tc.ToString() == "0:0:0");

    // Test rollover
    TimeCode tc3 = TimeCode(3, 71, 3801);
    assert(tc3.ToString() == "5:14:21");

    cout << "PASSED!" << endl << endl;
}

void TestGetComponents()
{
    cout << "Testing GetComponents" << endl;

    unsigned int h;
    unsigned int m;
    unsigned int s;

    TimeCode tc = TimeCode(5, 2, 18);

    tc.GetComponents(h, m, s);

    assert(h == 5 && m == 2 && s == 18);

    cout << "PASSED!" << endl << endl;
}

void TestSubtract()
{
    cout << "Testing Subtract" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);

    TimeCode tc3 = tc1 - tc2;

    assert(tc3.ToString() == "0:10:0");

    TimeCode tc4 = TimeCode(1, 15, 45);

    try
    {
        TimeCode tc5 = tc1 - tc4;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Negative TimeCodes are not allowed.
    }

    cout << "PASSED!" << endl << endl;
}

void TestSetMinutes()
{
    cout << "Testing SetMinutes" << endl;

    TimeCode tc = TimeCode(8, 5, 9);

    tc.SetMinutes(15);
    assert(tc.ToString() == "8:15:9");

    try
    {
        tc.SetMinutes(80);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Invalid minutes should leave the TimeCode unchanged.
    }

    assert(tc.ToString() == "8:15:9");

    cout << "PASSED!" << endl << endl;
}

int main()
{
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();
    TestSubtract();
    TestSetMinutes();

    // Test comparisons
    TimeCode a = TimeCode(1, 0, 0);
    TimeCode b = TimeCode(0, 30, 0);

    assert(a > b);
    assert(a != b);
    assert(a == TimeCode(1, 0, 0));
    assert(b < a);
    assert(b <= a);
    assert(a >= b);

    // Test multiplication and division
    assert((a * 0.5).ToString() == "0:30:0");
    assert((a / 2).ToString() == "0:30:0");

    // Test getters
    TimeCode c = TimeCode(4, 15, 32);

    assert(c.GetHours() == 4);
    assert(c.GetMinutes() == 15);
    assert(c.GetSeconds() == 32);

    // Test setters and reset
    TimeCode d = TimeCode(2, 10, 20);

    d.SetHours(5);
    assert(d.ToString() == "5:10:20");

    d.SetSeconds(45);
    assert(d.ToString() == "5:10:45");

    d.reset();
    assert(d.ToString() == "0:0:0");

    // Test addition
    TimeCode e = TimeCode(1, 0, 0);
    TimeCode f = TimeCode(0, 30, 0);

    assert((e + f).ToString() == "1:30:0");

    cout << "PASSED ALL TESTS!!!" << endl;

    return 0;
}
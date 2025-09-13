#include <cstdio>
#include <ctime>


int main(int argc, char* argv[]) {
    time_t now;
    struct tm* timestamp;
    char const* weekday[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday"
    };

    char const* month[] = {
        "January", "February", "March", "April",
		"May", "June", "July", "August",
		"September", "October", "November", "December"
    };

    time(&now);

    timestamp = localtime(&now);

    printf("Today is %s, %s %d %d\n",
        weekday[timestamp->tm_wday],
        month[timestamp->tm_mon], 
        timestamp->tm_mday,
        timestamp->tm_year + 1900);

    return 0;
}
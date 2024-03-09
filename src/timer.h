int *timer_status= nullptr;
int *timer_hour = nullptr;
int *timer_min = nullptr;
int *timer_sec = nullptr;
int *timer_day = nullptr;
int *timer_month = nullptr;
int *timer_year = nullptr;

int *timer_now_hour = nullptr;
int *timer_now_min = nullptr;
int *timer_now_timer_hour = nullptr;
int *timer_now_timer_min = nullptr;
bool *timer_timer_now = nullptr;

int *timer_start1_hour = nullptr;
int *timer_start1_min = nullptr;
bool *timer_timer1 = nullptr;

int *timer_start2_hour = nullptr;
int *timer_start2_min = nullptr;
bool *timer_timer2 = nullptr;

int *timer_mowtime_hour = nullptr;
int *timer_mowtime_min = nullptr;

bool *timer_emergency;

void setup_timer(
    int *c_hour, int *c_min, int *c_sec,
    int *c_day, int *c_month, int *c_year,
    int *c_status,
    int *c_mow_h, int *c_mow_m,
    int *c_now_h, int *c_now_m, int *c_now_timer_h, int *c_now_timer_m,
    bool *c_timer_now,
    int *c_start1_h, int *c_start1_m, bool *c_timer1,
    int *c_start2_h, int *c_start2_m, bool *c_timer2,
    bool *c_emergency) {
    
    timer_hour = c_hour;
    timer_min = c_min;
    timer_sec = c_sec;
    timer_day = c_day;
    timer_month = c_month;
    timer_year = c_year;
    timer_status = c_status;
    timer_mowtime_hour = c_mow_h;
    timer_mowtime_min = c_mow_m;

    timer_now_hour = c_now_h;
    timer_now_min = c_now_m;
    timer_now_timer_hour = c_now_timer_h;
    timer_now_timer_min = c_now_timer_m;
    timer_timer_now = c_timer_now;

    timer_start1_hour = c_start1_h;
    timer_start1_min = c_start1_m;
    timer_start2_hour = c_start2_h;
    timer_start2_min = c_start2_m;
    timer_timer1 = c_timer1;
    timer_timer2 = c_timer2;

    timer_emergency = c_emergency;
}

void check_timer()
{
    if ((*timer_start1_hour <= *timer_hour) && (*timer_start1_min <= *timer_min)
        && ((*timer_start1_hour + *timer_mowtime_hour) >= *timer_hour) 
        && ((*timer_start1_min + *timer_mowtime_min) >= *timer_min) 
        && not *timer_emergency)
    {
        *timer_timer1 = true;
        *timer_status = 0;
    }
    else{
        *timer_timer1 = false;
    }
    if (*timer_start2_hour <= *timer_hour && *timer_start2_min <= *timer_min 
        && ((*timer_start2_hour + *timer_mowtime_hour) >= *timer_hour) 
        && ((*timer_start2_min + *timer_mowtime_min) >= *timer_min)
        && not *timer_emergency)
    {
        *timer_timer2 = true;
        *timer_status = 0;
    }
    else{
        *timer_timer2 = false;
    }
    if (*timer_timer_now && (*timer_now_timer_hour + *timer_now_hour - *timer_hour) <= 0 
        && (*timer_now_timer_min + *timer_now_min - *timer_min) <= 0)
    {
        *timer_timer_now = false;
    }
    if(*timer_emergency or *timer_status != 0){
        *timer_timer_now = false;
    }
    if(not *timer_timer1 && not *timer_timer2 && not *timer_timer_now && *timer_status != 1){
        *timer_status = 2;
    }
}

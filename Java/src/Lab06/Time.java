package Lab06;

public class Time {
    private int h;
    private int m;
    private int s;

    public Time(int hours, int minutes, int seconds) {
        h = hours;
        m = minutes;
        s = seconds;
    }

    public boolean isEqual(Time t) {
        return h == t.h && m == t.m & s == t.s;
    }

    public int calculateDifferenceInSeconds(Time t){
        return Math.abs(h - t.h) * 3600 + Math.abs(m - t.m) * 60 + Math.abs(s - t.s);
    }
}

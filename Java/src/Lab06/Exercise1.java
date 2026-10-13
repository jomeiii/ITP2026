package Lab06;

public class Exercise1 {
    public static void main(String[] args) {
        int x = 67;
        int y = 2000;
        int temp = x;

        x = y;
        y = temp;

        System.out.println("X: " + x + "\nY: " + y);
    }
}

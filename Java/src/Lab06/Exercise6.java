package Lab06;

import java.util.Scanner;

public class Exercise6 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int fahrenheit = scanner.nextInt();
        float celsius = (fahrenheit - 32) * 5 / 9f;
        System.out.println("Converted temperature is " + celsius);
    }
}

package Lab06;

import java.util.Scanner;

public class Exercise8 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int decimalNumber = scanner.nextInt();

        System.out.println("Binary: " + Integer.toBinaryString(decimalNumber));
        System.out.println("Binary: " + Integer.toHexString(decimalNumber));
    }
}


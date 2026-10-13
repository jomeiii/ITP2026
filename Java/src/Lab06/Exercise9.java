package Lab06;

import java.util.Scanner;

public class Exercise9 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter count of number");
        int length = scanner.nextInt();
        int sum = 0;
        for (int i = 0; i < length; i++){
            int num = scanner.nextInt();
            sum += num;
        }

        System.out.println("Average value of array is " + sum / (float)length);
    }
}


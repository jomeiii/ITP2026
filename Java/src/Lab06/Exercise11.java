package Lab06;

import java.util.Scanner;

public class Exercise11 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter count of number");
        int length = scanner.nextInt();
        int[] array = new int[length];
        for (int i = 0; i < length; i++) {
            int num = scanner.nextInt();
            array[i] = num;
        }

        for (int i = 0; i < length; i++){
            for (int j = i + 1; j < length; j++){
                if (array[i] == array[j]){
                    System.out.print(array[i] + " ");
                    break;
                }
            }
        }
    }
}


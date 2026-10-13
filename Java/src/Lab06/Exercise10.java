package Lab06;

import java.util.Scanner;

public class Exercise10 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter count of number");
        int length = scanner.nextInt();
        int[] array = new int[length];
        for (int i = 0; i < length; i++){
            int num = scanner.nextInt();
            array[i] = num;
        }

        System.out.println("Enter number for insert");
        int insertNumber = scanner.nextInt();
        System.out.println("Enter index for insert");
        int index = scanner.nextInt();

        int[] newArray = new int[length + 1];
        for (int i = 0; i < length + 1; i++){
            if (i < index){
                newArray[i] = array[i];
            }
            else if (i == index){
                newArray[i] = insertNumber;
            }
            else{
                newArray[i] = array[i - 1];
            }
        }

        System.out.println("New array");
        for (int i = 0; i < length + 1; i++){
            System.out.print(newArray[i] + " ");
        }
    }
}


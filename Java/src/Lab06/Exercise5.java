package Lab06;

import java.util.Scanner;

public class Exercise5 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] vowels = new char[]{'a', 'e', 'i', 'o', 'u'};
        int counter = 0;
        String s = scanner.nextLine();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            for (int j = 0; j < vowels.length; j++) {
                if (Character.toLowerCase(c) == vowels[j]){
                    counter++;
                    break;
                }
            }
        }

        System.out.println("Vowels count is equal to " + counter);
    }
}

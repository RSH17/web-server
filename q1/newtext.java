import java.io.*;
import java.util.*;

public class ProjectAnagram {

   public static String sort(String s) {
        char[] c = s.toCharArray();
        Arrays.sort(c);
        return String.valueOf(c);
    }

    public static void main(String[] args) throws FileNotFoundException {
        Map<String, List<String>> words = new HashMap<>();
        try (Scanner in = new Scanner(new File(args[0]))) {
            while (in.hasNext()) {
                String word = in.next();
                String sorted = sort(word);
                List<String> list = words.get(sorted);
                if (list == null)
                    words.put(sorted, list = new ArrayList<>());
                list.add(word);
            }
        }
        Scanner in = new Scanner(System.in);
        while (true) {
            System.out.print("Enter word (or press ENTER to quit): ");
            if (!in.hasNextLine()) break;
            String s = in.nextLine();
            if (s.length() == 0) break;
            System.out.println(words.get(sort(s)));
        }
    }
}
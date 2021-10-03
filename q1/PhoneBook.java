import java.util.HashMap;
import java.util.Scanner;

public class PhoneBook  
{
    public static void main(String args[]) 
    { 
        String value; 
        HashMap<Integer, String> hashMap = new HashMap<Integer, String>(); 
        hashMap.put( new Integer(997768),"Mother" ); 

        Scanner scan = new Scanner(System.in);  
        System.out.println("Enter an phone number :");  
        int x = scan.nextInt();  
        value = (String) hashMap.get(new Integer(x));  
        
        if (value != null) {
           System.out.println("Value is:" + value); 
        } else {
           System.out.println("Value is 0");
        }

         
    } 
} 
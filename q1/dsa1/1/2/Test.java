import java.util.*;
import java.io.*;

class LinkedListNode{
	LinkedListNode next;
	int number;
	String name;
	
	public LinkedListNode(int numberVal,String nameVal){
		number = numberVal;
		name = nameVal;
		next = null;
	}
}

class HashTable{
	private LinkedListNode[] table;
	private int count;
	
	public HashTable(int tableSize){
		table = new LinkedListNode[tableSize];
		count = 0;
	}
	
	public void insert(int numberVal,String nameVal){
		count++;
		int pos = getHash(numberVal);
		LinkedListNode ptr = new LinkedListNode(numberVal,nameVal);
		
		if(table[pos] == null){
			table[pos] = ptr;
		}else{
			ptr.next = table[pos];
			table[pos] = ptr;
		}
	}
	
	public String getName(int numberVal){
		int pos = getHash(numberVal);
		LinkedListNode start = table[pos];
		while(start != null ){
			if(start.number == numberVal){
				return start.name;
			}else{
				start = start.next;
			}
			
		}
		
		return "0";
	}
	
	private int getHash(Integer key){
		int hash = key.hashCode();
		hash %= table.length;
		if(hash < 0){
			hash += table.length;
		}
		return hash;
	}
	
}


class Test{
	public static void main(String args[]){
		
		try{
			
			File file = new File("PhoneBook.txt");
			FileReader fr = new FileReader(file);
			BufferedReader br = new BufferedReader(fr);
			String line;
			HashTable ht = new HashTable(10);
			while((line=br.readLine()) != null){
				String[] str = line.split("-");
				ht.insert(Integer.parseInt(str[0]),str[1]);
			}
			fr.close();
			//ht.display();
			Scanner input = new Scanner(System.in);

			char ch;
			do{
				
				System.out.println("\nSearch number : ");
				System.out.println("Number belongs to :" + ht.getName(input.nextInt()));
							
				System.out.println("\ntry again?");
				ch = input.next().charAt(0);
			}while(ch == 'y');
			
		}catch(IOException e){
			e.printStackTrace();
		}

		
	}
}







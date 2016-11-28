import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;

public class SecretSanta
{	
	public static void main(String[] args)
	{
		ArrayList<String> from = new ArrayList<>();
		ArrayList<String> to = new ArrayList<>();
		ArrayList<String> inter = new ArrayList<>();
		Random rand = new Random(System.currentTimeMillis());
		int max = 0;
		
		Scanner input = new Scanner(System.in);
		System.out.print("Please enter the names of all participants\nFormat: \"Person One, Person Two, Person Three\"\n>> ");
		String[] tmp = input.nextLine().split(",");
		
		for (int i = 0; i < tmp.length; i++)
		{
			if (tmp[i].trim().length() > max)
				max = tmp[i].trim().length();
			
			from.add(tmp[i].trim().toLowerCase());
			inter.add(tmp[i].trim().toLowerCase());
		}
		
		if (from.size() < 3)
		{
			System.out.println("You must have at least 3 people");
			System.exit(1);
		}

		for (int i = 0; i < from.size(); i++)
		{
			int loc = rand.nextInt(inter.size());

			if (loc == i)
			{
				i--;
				continue;
			}

			to.add(inter.get(loc));
			inter.remove(loc);
		}

		for (int i = 0; i < from.size(); i++)
		{
			System.out.println(String.format("%1$-" + (max+3) + "s", from.get(i)) + " buys for " + to.get(i));
		}
		
		System.exit(0);
	}
}

import java.util.Scanner;

public class Tester{
     

public static void main(String args[]){

    SubmissionChoices object = new SubmissionChoices();
    Scanner scan = new Scanner(System.in);
    String inputScores = "";
    inputScores = scan.nextLine();
    object.parseInput(inputScores);
    System.out.println(object.getChoices());
  }
}

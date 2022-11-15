import java.util.ArrayList;
import java.util.Iterator;

public class SubmissionChoices{
    /* private member variables.  Do not change these*/
    private double A1;
    private double A2;
    private double A3;
    private String choices;


    private int subChoice;

    
    public void setChoices(double num1,double num2, double num3){
        if (num1>100 && num2>100  && num3>100){
            subChoice = 1;
        }
        else if (num1<=100 && num2>100  && num3>100){
            subChoice = 2;
        }
        else if (num1<=100 && num2<=100  && num3>100){
            subChoice = 3;
        }
        else if (num1<=100 && num2<=100  && num3<=100){
            subChoice = 4;
        }
    }

    public String getChoices(){
        if(subChoice == 1){
            choices = "A1";
        }
        else if (subChoice == 2){
            choices = "A1R A2";
        }
        else if (subChoice == 3){
            choices = "A2R A3";
        }
        else if (subChoice == 4){
            choices = "A3R";
        }
        return choices;
    }


    public void parseInput(String inputLine){
       
    String singles[] = inputLine.split(",");
    A1 = Double.parseDouble(singles[0]);
    A2 = Double.parseDouble(singles[1]);
    A3 = Double.parseDouble(singles[2]);
    setChoices(A1,A2,A3);
  
    }


}

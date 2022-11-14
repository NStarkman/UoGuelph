package connectfour;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/* you will need to add test methods and likely change the
setup method as well.  The samples that are here are just so that
you can see how junit works.

Tests are run on build unless specifically excluded with -x test.
The test results are reported in the reports subfolder of the build directory */


public class BoardTest{
    private Board tester;
    private Board tester2;
    private Board diagTest;
    private Board horzTest;
    private Board horzTest2;
    private Board more2Test;
    private Board loadedTest;
    private Board emptyTest;
    private String fakeBoard = 
    "0,0,0,0,0,0,0\n0,0,0,0,0,0,0\n0,0,0,0,0,0,0\n0,0,0,0,0,0,0\n0,0,0,0,0,0,0\n0,0,0,0,0,0,0\n";
    private String fullFakeBoard = 
    "1,1,1,1,1,1,1\n1,1,1,1,1,1,1\n1,1,1,1,1,1,1\n1,1,1,1,1,1,1\n1,1,1,1,1,1,1\n1,1,1,1,1,1,1\n";

    @Before
    public void setup(){
        //set up for the test
        tester = new Board();
        tester2 = new Board();
        emptyTest = new Board();
        loadedTest = new Board();
        diagTest = new Board();
        horzTest = new Board();
        horzTest2 = new Board();
        more2Test = new Board();
        loadedTest.loadBoard("all1.csv");
        emptyTest.loadBoard("file2.csv");
        diagTest.loadBoard("exampleBoard.csv");
        horzTest.loadBoard("file.csv");
        horzTest2.loadBoard("gamer.csv");
        more2Test.loadBoard("tree.csv");


    }
    
    @Test
    public void placeSymbol(){
        Assert.assertEquals(loadedTest.placeSymbol(6,1), -1);
        Assert.assertEquals(loadedTest.placeSymbol(6,2), -1);

    }

    @Test
    public void isBoardFull(){

        Assert.assertFalse(tester.isBoardFull());
        Assert.assertTrue(loadedTest.isBoardFull());
        
    }
    @Test
    public void boardToString(){
        Assert.assertEquals(tester.boardToString(), fakeBoard);
        Assert.assertEquals(loadedTest.boardToString(), fullFakeBoard);
    }
    @Test
    public void saveBoard(){
        Assert.assertEquals(tester2.saveBoard(""), 1);

    }
    @Test
    public void loadBoard(){
        Assert.assertEquals(tester.loadBoard("emptydoc.csv"), -1);
        Assert.assertEquals(tester.loadBoard("filenew.csv"), -1);
        Assert.assertEquals(tester.loadBoard("newBoard.csv"), -1);
        Assert.assertEquals(tester.loadBoard("fileNo.csv"), -1);

    }
    @Test
    public void getDiagonalWinnerStatus(){
        Assert.assertEquals(diagTest.getDiagonalWinnerStatus(), 1);
        Assert.assertEquals(horzTest.getDiagonalWinnerStatus(), 0);
        Assert.assertEquals(horzTest2.getDiagonalWinnerStatus(), 0);
    }
    @Test
    public void getHorzVertWinner(){
        Assert.assertEquals(diagTest.getHorzVertWinner(), 0);
        Assert.assertEquals(horzTest.getHorzVertWinner(), 1);
        Assert.assertEquals(horzTest2.getHorzVertWinner(), 2);
    }
    @Test
    public void getWinnerStatus(){
        Assert.assertEquals(diagTest.getWinnerStatus(), 1);
        Assert.assertEquals(horzTest.getWinnerStatus(), 1);
    }
    @Test
    public void calcTurn(){
        Assert.assertEquals(horzTest2.calcTurn(), 2);
        Assert.assertEquals(more2Test.calcTurn(), 1);
    }
    public void switchTurn(){
        Assert.assertEquals(tester.switchTurn(1), 2);
    }
 }
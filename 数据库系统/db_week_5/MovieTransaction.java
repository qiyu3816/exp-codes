import java.util.*;
import java.io.*;
import java.text.*;
import java.sql.*;

/**
 * A class representing the driver program to the
 * SSD7 transaction exercise.
 *
 * @author CTE
 * @version 1.0
 */

public class MovieTransaction
{
    /**
     * main method.
     *
     */
    public static void main( String [] args )
    {
	
	String [] movienames = new String[10];
	String [] movietimes = new String[10];
	String sqlquery = null;
	String moviename = null;
	String movietime = null;
	ResultSet rset = null;
	Connection conn = null;
	Statement stmt = null;
	BufferedReader keyIn = null;
	String url = "jdbc:postgresql-local:Movie";
	String username = "qiyu";
	String password = "1039lrh";
	int position = 0, choice, movie_id, numseats, availableseats;
	
	try
	    {
		// Create a BufferedReader to read input from the keyboard.
		keyIn = new BufferedReader(new InputStreamReader(System.in));
		
		// Load the PostgreSQL JDBC driver
		Class.forName("org.postgresql.Driver");

		// Create a connection to the database.
		conn = DriverManager.getConnection( url, username,password );

		// Create a statement object.
		stmt = conn.createStatement();

		// Begin a new, chained, transaction.
        //>>>>>>>>>>>>>>>>>>>>>>>> 事务开始
		stmt.executeUpdate( "Begin Work" );

		// 隔离等级设置为serializable，避免用户读取被修改或增添但未提交的数据，避免用户查询到的数据不一致
        // Set the transaction isolation level to serializable 
		stmt.executeUpdate( "set transaction isolation level serializable" );

		System.out.println( "Welcome to the movie theater!" );
		
		// Query the titles currently playing.
		String SQLQuery = "select distinct title from movie";
		rset = stmt.executeQuery( SQLQuery );
		while( rset.next() )
		    {
			movienames[rset.getRow()] = rset.getString( "title" );
			System.out.println( rset.getRow() + ": " + rset.getString("title") );
		    }

		// 先显示查询结果用户再选择 Query the id for this movie.
		sqlquery = new String( "select movie_id from movie where title='" + moviename + "'" );
		rset = stmt.executeQuery( sqlquery );
		rset.next();
		movie_id = rset.getInt( "movie_id" );

        //<<<<<<<<<<<<<<<<<<<<<<<< 事务结束
		stmt.executeUpdate( "commit" );

		// 用户输入置于事务边界之外 Ask the user what movie he wants to see.
		System.out.print( "Enter the number of the movie you want to see:" );
		choice = Integer.parseInt(keyIn.readLine());
		moviename = movienames[(choice)];

		// Begin a new, chained, transaction.
        //>>>>>>>>>>>>>>>>>>>>>>>> 事务开始
		stmt.executeUpdate( "Begin Work" );
		
		// 先显示查询结果用户再选择场次 Query the available times for the chosen movie.
		sqlquery = new String( "select distinct movie_time from showing where movie_id =" + movie_id );
		rset = stmt.executeQuery( sqlquery );
		while( rset.next() )
		    {
			movietimes[(rset.getRow())] = rset.getString( "movie_time" );
                        System.out.println( rset.getRow() + ": " + rset.getString( "movie_time" ) );
                    }

        //<<<<<<<<<<<<<<<<<<<<<<<< 事务结束
		stmt.executeUpdate( "commit" );

		// 用户输入置于事务边界之外 Ask the user what showing he wants to see.
		System.out.println( "Enter the number of the time you want to see: " );
		choice = Integer.parseInt( keyIn.readLine() );
		movietime = movietimes[(choice)];

		// 用户输入置于事务边界之外 Ask the user how many seats he wants.
		System.out.println( "Please enter the number of seats that you want to buy: " );
		numseats = Integer.parseInt( keyIn.readLine() );

		// Begin a new, chained, transaction.
        //>>>>>>>>>>>>>>>>>>>>>>>> 事务开始
		stmt.executeUpdate( "Begin Work" );

		// 先查询剩余座位再与用户输入的座位数比较 Query the database for the number of available standrd seats.
		sqlquery = new String( "select available_standard_seats from showing where movie_id = " + movie_id );
		rset = stmt.executeQuery( sqlquery );
		rset.next();
		availableseats = rset.getInt( "available_standard_seats" );

		if (availableseats < numseats)
		    {
			System.out.println( "We are sorry, there are not that many seats available for this showing!" );
			System.out.println( "Please try again!" );
			stmt.executeUpdate( "rollback" ); //<<<<<<<<<<<<<<<<<<<<<<<< 事务结束
			conn.close();
			System.exit(0);
		    }
		// If there are enough available seats, update the database for the reservation and commit the transaction.
		else
		    {
			sqlquery = new String( "update showing set available_standard_seats=" + (availableseats-numseats) + " where movie_id=" + movie_id + " and movie_time='" + movietime + "'" );
			stmt.executeUpdate( sqlquery );
			stmt.executeUpdate( "commit" ); //<<<<<<<<<<<<<<<<<<<<<<<< 事务结束
			System.out.println( "Your tickets have now been purchased, enjoy the show!" );
			conn.close();
		    }
	    }
	catch( SQLException e )
	    {
		System.out.println( "An exception has occured!" );
		e.printStackTrace();
		try
		    {
			stmt.executeUpdate("rollback");
			conn.close();
		    }
		catch( Exception exception )
		    {
			exception.printStackTrace();
		    }
		System.out.println( "Transaction has been rolled back!" );
	    }
	catch( Exception e )
	    {
		System.out.println( "A non database error has occured!" );
		try
		    {
			stmt.executeUpdate("rollback");
			conn.close();
		    }
		catch( Exception exception )
		    {
			exception.printStackTrace();
		    }
		System.out.println( "Transaction has been rolled back!" );
		e.printStackTrace();
	    }
    }	
}

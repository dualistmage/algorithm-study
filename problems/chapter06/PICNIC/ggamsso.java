package algostudy;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Vector;

public class Picnic
{
	public static void main(String[] args) throws NumberFormatException, IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		final int maxTestCase = Integer.parseInt( br.readLine() );
		
		for( int posInput = 0; posInput < maxTestCase; ++posInput )
		{
			String[] classInfo = br.readLine().split( "\\s+" );
			String[] friendsInfo = br.readLine().split( "\\s+" );
			
			if( classInfo.length != 2 )
				continue;
			if( friendsInfo.length % 2 != 0 )
				continue;
			
			final int maxStudentInClass = Integer.parseInt( classInfo[0] );
			final int maxFriendInClass = Integer.parseInt( classInfo[1] );
			final int maxFriendFairInClass = maxStudentInClass / 2;
			
			Map< Integer, Vector<Integer> > friendInfoMap = new TreeMap< Integer, Vector<Integer> >();
			
			for( int pos = 0; pos < maxFriendInClass*2; pos += 2 )
			{
				int x = Integer.parseInt( friendsInfo[pos] );
				int y = Integer.parseInt( friendsInfo[pos+1] );
				
				if( x > y )
				{
					int temp = x;
					x = y;
					y = temp;
				}
				
				if( friendInfoMap.containsKey(x) == false )
					friendInfoMap.put( x, new Vector<Integer>() );
				
				if( friendInfoMap.get(x).contains(y) == false )
				{
					friendInfoMap.get(x).add(y);
					Collections.sort( friendInfoMap.get(x) );
				}
			}
			
			{
				int x = 0, y = 0;
				int maxCount = 0;
				
				Vector< Friend > pairStack = new Vector<Friend>();
				
				boolean[] picked = new boolean[maxStudentInClass];
				resetPicked(picked);
				
				Vector< Iterator<Integer> > iterVec = new Vector< Iterator<Integer> >();
				iterVec.add( friendInfoMap.get(x).iterator() );
				
				while( true )
				{	
					if( iterVec.lastElement().hasNext() == false )
					{
						iterVec.remove( iterVec.size()-1 );
						picked[pairStack.lastElement().x] = false;
						picked[pairStack.lastElement().y] = false;
						pairStack.remove( pairStack.size()-1 );
					
						if( pairStack.isEmpty() == true )
							break;
						
						x = pairStack.lastElement().x;
						picked[pairStack.lastElement().y] = false;
						
						continue;
					}
					
					y = iterVec.lastElement().next();
					if( picked[y] == true )
						continue;
					
					// System.out.print( String.format("(%d,%d) ", newX, newY) );
					
					picked[x] = true;
					picked[y] = true;
					
					if( (pairStack.isEmpty() == false) && (pairStack.lastElement().x == x) )
						pairStack.remove( pairStack.size()-1 );
					pairStack.add( new Friend(x, y) );
					
					if( pairStack.size() == maxFriendFairInClass )
					{
						//System.out.println();
						
						++maxCount;
					}
					
					x = getNewX(picked);
					if( x == -1 )
					{
						iterVec.remove(iterVec.size() -1);
						picked[pairStack.lastElement().x] = false;
						picked[pairStack.lastElement().y] = false;
						pairStack.remove( pairStack.size()-1 );
						
						if( pairStack.isEmpty() == true )
							break;
						
						x = pairStack.lastElement().x;
						picked[pairStack.lastElement().y] = false;
						
						continue;
					}
						
					iterVec.add( friendInfoMap.get(x).iterator() );
				}
				
				System.out.println(maxCount);
			}
		}
	}
	
	public static void resetPicked( boolean[] picked )
	{
		for( int pos = 0; pos < picked.length; ++pos )
		{
			picked[pos] = false;
		}
	}
	
	public static int getNewX( boolean[] picked )
	{
		for( int pos = 0; pos < picked.length; ++pos )
		{
			if( picked[pos] == false )
				return pos;
		}
		
		return -1;
	}
	
	public static class Friend
	{
		public int x;
		public int y;
		
		public Friend( int newX, int newY )
		{
			x = newX;
			y = newY;
		}
	}
}

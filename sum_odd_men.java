package rough1;
import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;
/**
*
* @author Bhargavi
*/
public class Rough1 {
/**
* @param args the command line arguments
*/
public static void main(String[] args){
BigInteger fact1;
int c=0;
BigInteger fact=BigInteger.ONE;
BigInteger bi1,bi2,s;
s=new BigInteger("0");
bi2=new BigInteger("10");
Scanner ob=new Scanner(System.in);
int f=ob.nextInt();
for(int i=2;i<=f;i++){
fact=fact.multiply(new BigInteger(String.valueOf(i)));
}
fact1=fact;
while(fact1!=BigInteger.ZERO)
{
c++;
bi1=fact1;
fact1=bi1.divide(bi2);
}
if(c%2==0)
{
bi1=fact;
fact=bi1.divide(bi2);
while(fact!=BigInteger.ZERO){
s=s.add(fact.mod(bi2));
fact=fact.divide(bi2);
fact=fact.divide(bi2);
}
}
else
{
while(fact!=BigInteger.ZERO){
s=s.add(fact.mod(bi2));
fact=fact.divide(bi2);
fact=fact.divide(bi2);
}
}
System.out.println(s);
}
}

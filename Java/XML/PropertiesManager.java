import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.Properties;

 import java.io.*;
 import org.w3c.dom.Document;
 import org.w3c.dom.Node;
 import javax.xml.parsers.*;

public class PropertiesManager 
{
	public static void main(String[] args)  throws Exception
    {
    	Properties playGameName = new Properties();
    	playGameName.setProperty("tes", "sss");
    	    	playGameName.setProperty("h", "sss");
    	try(OutputStream xmlData = new FileOutputStream("gameName.xml", true))
    	{
    		playGameName.storeToXML(xmlData, "ゲーム内容");
    	}
    	
    	LoadXML();
    }
    
    
    public static void LoadXML()
    {
    	Document document= DocumentBuilderFactory
                          .newInstance()
                          .newDocumentBuilder()
                          .parse(new File("helloWorld.xml"));
 
 
     	Node node=document.getDocumentElement();
     	Node childNode=node.getFirstChild()
 
     	System.out.println(childNode);
    }
}
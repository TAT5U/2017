using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class Binding
{
	// ネイティブコードを変換したやつを呼び出し
	// 1つにつき1つ
	[DllImport("__Internal")]

	// Objective-C++側の関数
	// Twitter
	private static extern void TweetShare(string sendText, string sendImagePath);

	[DllImport("__Internal")]

	//Facebook
	private static extern void FacebookShare(string sendImagePath);

	// Objective-C++側の関数を呼び出す
	public static void Tweet(string sendText, string sendImagePath)
	{
		TweetShare(sendText, sendImagePath);
	}

	public static void FacebookSend(string sendImagePath)
	{
		FacebookShare(sendImagePath);
	}
}

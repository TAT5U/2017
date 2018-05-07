using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneChange : MonoBehaviour {


	public string nextScene;


	// Use this for initialization
	void Start () {
		
	}
	

	// ボタンタッチされたら呼び出し
	public void pushButton () 
	{
			Application.LoadLevel(nextScene);
	}
}

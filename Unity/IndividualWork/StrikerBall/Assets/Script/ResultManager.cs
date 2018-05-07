using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ResultManager : MonoBehaviour 
{

	public void ClickTitle()
	{
		SceneManager.LoadScene(0);
	}

	public void ClickRetry()
	{
		SceneManager.LoadScene(1);
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ResultButtonClickScript : MonoBehaviour 
{
	public void ClickToTitle()
	{
		SceneManager.LoadScene(0);
	}

	public void ClickToRetry()
	{
		SceneManager.LoadScene(1);
	}
}

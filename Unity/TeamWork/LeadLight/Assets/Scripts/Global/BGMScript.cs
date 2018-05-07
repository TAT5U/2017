using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGMScript : MonoBehaviour 
{
	private AudioSource music;

	//// Use this for initialization
	void Awake () 
	{

		music = gameObject.GetComponent<AudioSource>();
		music.loop = true;

		//DontDestroyOnLoad(this);
	}

	public void BGMPlay()
	{
		music.Play();
	}
	public void BGMStop()
	{
		music.Pause();
	}
}

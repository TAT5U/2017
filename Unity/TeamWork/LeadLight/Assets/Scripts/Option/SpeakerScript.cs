using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SpeakerScript : MonoBehaviour 
{

	public Sprite speak;
	public Sprite speakNG;
	public ConfigScript config;
	public SoundScript sound;

	[SerializeField]private SoundScript ui_;



	// Use this for initialization
	void Start ()
	{
		if (config.GetSpeaker())
		{
			gameObject.GetComponent<Image>().sprite = speak;
		}
		else
		{
			gameObject.GetComponent<Image>().sprite = speakNG;
		}
	}

	public void ClickImage()
	{
		ui_.SoundPlay(3);
		if (gameObject.GetComponent<Image>().sprite.name == speak.name)
		{
			gameObject.GetComponent<Image>().sprite = speakNG;
			config.SetSpeaker(false);
			sound.SetMute(true);
		}
		else
		{
			gameObject.GetComponent<Image>().sprite = speak;
			config.SetSpeaker(true);
			sound.SetMute(false);
		}
	}
}

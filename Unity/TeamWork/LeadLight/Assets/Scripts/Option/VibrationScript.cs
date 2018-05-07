using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class VibrationScript : MonoBehaviour 
{
	public Sprite vibration;
	public Sprite vibrationNG;

	public ConfigScript config;

	[SerializeField]private SoundScript ui_;

	// Use this for initialization
	void Start () 
	{
		if (config.GetVibration())
		{
			gameObject.GetComponent<Image>().sprite = vibration;
		}
		else
		{
			gameObject.GetComponent<Image>().sprite = vibrationNG;
		}
	}

	public void ClickImage()
	{
		ui_.SoundPlay(3);
		if (gameObject.GetComponent<Image>().sprite.name == vibration.name)
		{
			gameObject.GetComponent<Image>().sprite = vibrationNG;
			config.SetVibration(false);
		}
		else
		{
			gameObject.GetComponent<Image>().sprite = vibration;

				config.SetVibration(true);
		}
		SwitchingConfig();
	}

	public void SwitchingConfig()
	{
		// つけなくても動作するが、念のため判別する
		if ((Application.platform == RuntimePlatform.Android) || (Application.platform == RuntimePlatform.IPhonePlayer))
		{
			if (config.GetVibration())
			{
				Handheld.Vibrate();
			}
		}
	}
}

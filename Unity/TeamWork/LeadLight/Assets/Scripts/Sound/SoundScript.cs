using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundScript : MonoBehaviour {

	public AudioSource BGM;
	public AudioSource UI;

	[Tooltip("3: Optionなどのクリック音\n4: 閉じるときの音")]
	public AudioClip[] uiClip = new AudioClip[5];

	public ConfigScript config;

	//// Use this for initialization
	void Start()
	{
		SetMute(!config.GetSpeaker());
	}

	public void SetMute(bool flg)
	{
		BGM.mute = flg;
		UI.mute = flg;
	}

	public void SoundPlay()
	{
		BGM.Play();
	}

	public void SoundPlay(int num)
	{
		try
		{
			UI.clip = uiClip[num];
			UI.Play();
		}
		catch (System.Exception ex)
		{
			print("Sound Error");
		}
	}

	public bool IsPlaying()
	{
		return UI.isPlaying;
	}
}

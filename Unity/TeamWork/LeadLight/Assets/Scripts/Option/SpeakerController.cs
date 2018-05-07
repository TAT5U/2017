using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SpeakerController : MonoBehaviour {

    public Sprite speak, speakNG;
    public SoundScript sound;
    public ConfigScript config;
	// Use this for initialization
	void Start () {
        if (config.GetSpeaker())
        {
            gameObject.GetComponent<Image>().sprite = speak;
        }
        else
        {
            gameObject.GetComponent<Image>().sprite = speakNG;
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    public void ClickImage()
    {
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

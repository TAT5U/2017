using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartScript : MonoBehaviour
{

	public ConfigScript config;

	public LevelManager manager;

	public SoundScript uiSound;

	//private FadeAnimationScript flash;

	private bool clickFlg;

	private int clickCount_ = 0;
	public AudioSource titleBGM;

	// HACK: 同じスクリプトが入るのであまり良くない
	//		 Fadeのスクリプトがクソのため
	// 		 時間がないのでこれで対処
	[SerializeField]private FadeAnimationScript[] fade = new FadeAnimationScript[2];

	void Awake()
	{
		//flash = GetComponent<FadeAnimationScript>();
		config.SetInitialize();
	}

	void Start()
	{
		if (!config.GetSpeaker())
		{
			titleBGM.mute = true;
		}

		if (config.GetBackName() == "Retry")
		{
			gameObject.transform.SetAsLastSibling();
			config.SetBackName("Title");
			manager.GameStart();
			gameObject.SetActive(false);
		}
		config.SetBackName("Title");
		clickFlg = false;
	}

	void Update()
	{
		if (clickFlg && fade[0].FadeJudge())
		{
			manager.GameStart();
			gameObject.SetActive(false);
		}
	}

	public void ClickImage()
	{
		if (clickCount_ <= 0)
		{

			gameObject.transform.SetAsLastSibling();
			uiSound.SoundPlay(0);
			fade[0].FadeOutStart(gameObject.transform.Find("Start Event Trigger/Start Image").gameObject);

			foreach (Transform child in gameObject.transform.Find("Start Event Trigger"))
			{
				if (child.name != "Image")
				{
					fade[1].FadeOutStart(child.gameObject);
				}
			}
			clickFlg = true;

			clickCount_++;
		}
	}
}
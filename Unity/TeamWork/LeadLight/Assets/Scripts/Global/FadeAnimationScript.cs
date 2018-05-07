using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeAnimationScript : MonoBehaviour
{
	[SerializeField]
	private float fadeInSpeed;
	[SerializeField]
	private float fadeOutSpeed;

	[SerializeField]
	private float flashInterval;

	private Color fadeInColor;
	private Color fadeOutColor;

	private bool fadeFlg;
	private bool fadeGenre;

	private GameObject objectName;
	private GameObject flashObjectName;

	// FadeIn
	public void FadeInStart(Text dispObject)
	{
		objectName = dispObject.gameObject;
		SetFadeIn();
		objectName.GetComponent<Text>().color = new Color(objectName.GetComponent<Text>().color.r, objectName.GetComponent<Text>().color.g, objectName.GetComponent<Text>().color.b, fadeInColor.a);
		SetFadeGenre(false);

		StartCoroutine("FadeIn");
	}
	public void FadeInStart(GameObject dispObject)
	{
		objectName = dispObject;
		SetFadeIn();
		objectName.GetComponent<Image>().color = new Color(objectName.GetComponent<Image>().color.r, objectName.GetComponent<Image>().color.g, objectName.GetComponent<Image>().color.b, fadeInColor.a);
		SetFadeGenre(true);

		StartCoroutine("FadeIn");
	}


	// FadeOut
	public void FadeOutStart(Text dispObject)
	{
		objectName = dispObject.gameObject;
		SetFadeOut();
		objectName.GetComponent<Text>().color = new Color(objectName.GetComponent<Text>().color.r, objectName.GetComponent<Text>().color.g, objectName.GetComponent<Text>().color.b, fadeOutColor.a);
		SetFadeGenre(false);

		StartCoroutine("FadeOut");
	}
	public void FadeOutStart(GameObject dispObject)
	{
		objectName = dispObject;
		SetFadeOut();
		objectName.GetComponent<Image>().color = new Color(objectName.GetComponent<Image>().color.r, objectName.GetComponent<Image>().color.g, objectName.GetComponent<Image>().color.b, fadeOutColor.a);
		SetFadeGenre(true);

		StartCoroutine("FadeOut");
	}


	// Flash
	public void FlashStart(Text dispObject)
	{
		flashObjectName = dispObject.gameObject;
		SetFadeGenre(false);

		StartCoroutine("Flash");
	}
	public void FlashStart(GameObject dispObject)
	{
		flashObjectName = dispObject;
		SetFadeGenre(true);

		StartCoroutine("Flash");
	}


	// SetFadeColor
	private void SetFadeIn()
	{
		fadeFlg = false;
		fadeInColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
	}
	private void SetFadeOut()
	{
		fadeFlg = false;
		fadeOutColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
	}


	// SetFadeGenre
	private void SetFadeGenre(bool flg)
	{
		fadeGenre = flg;
	}
	private bool GetFadeGenre()
	{
		return fadeGenre;
	}


	// FadeIn Coroutine
	IEnumerator FadeIn()
	{
		while (true)
		{
			if (GetFadeGenre())
			{
				objectName.GetComponent<Image>().color = new Color(objectName.GetComponent<Image>().color.r, objectName.GetComponent<Image>().color.g, objectName.GetComponent<Image>().color.b, fadeInColor.a);
			}
			else
			{
				objectName.GetComponent<Text>().color = new Color(objectName.GetComponent<Text>().color.r, objectName.GetComponent<Text>().color.g, objectName.GetComponent<Text>().color.b, fadeInColor.a);
			}

			fadeInColor.a += fadeInSpeed;
			if (fadeInColor.a >= 1.0f)
			{
				fadeFlg = true;
				StopCoroutine("FadeIn");
			}
			yield return null;
		}
	}


	// FadeOut Coroutine
	IEnumerator FadeOut()
	{
		while (true)
		{
			if (GetFadeGenre())
			{
				objectName.GetComponent<Image>().color = new Color(objectName.GetComponent<Image>().color.r, objectName.GetComponent<Image>().color.g, objectName.GetComponent<Image>().color.b, fadeOutColor.a);
			}
			else
			{
				objectName.GetComponent<Text>().color = new Color(objectName.GetComponent<Text>().color.r, objectName.GetComponent<Text>().color.g, objectName.GetComponent<Text>().color.b, fadeOutColor.a);
			}

			fadeOutColor.a -= fadeOutSpeed;
			if (fadeOutColor.a <= 0.0f)
			{
				fadeFlg = true;
				//StopFlash();
				StopCoroutine("FadeOut");
			}
			yield return null;
		}
	}
	// Flash Coroutine
	//IEnumerator Flash()
	//{
	//	while (true)
	//	{
	//		if (GetFadeGenre())
	//		{
	//			flashObjectName.GetComponent<Image>().enabled = !flashObjectName.GetComponent<Image>().enabled;
	//		}
	//		else
	//		{
	//			flashObjectName.GetComponent<Text>().enabled = !flashObjectName.GetComponent<Text>().enabled;
	//		}
	//		yield return new WaitForSeconds(flashInterval);
	//	}
	//}


	// Flash Coroutine Stop
	//private void StopFlash()
	//{
	//	if (GetFadeGenre())
	//	{
	//		flashObjectName.GetComponent<Image>().enabled = false;
	//	}
	//	else
	//	{
	//		flashObjectName.GetComponent<Text>().enabled = false;
	//	}
	//	StopCoroutine("Flash");
	//}


	// Fade Flag
	public bool FadeJudge()
	{
		return fadeFlg;
	}
}
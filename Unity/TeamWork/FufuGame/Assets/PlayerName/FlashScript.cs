using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlashScript : MonoBehaviour
{
	[SerializeField]
	private float flashInterval;

	private bool fadeFlg;
	private bool fadeGenre;
	private GameObject flashObjectName;

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


	// SetFadeGenre
	private void SetFadeGenre(bool flg)
	{
		fadeGenre = flg;
	}
	private bool GetFadeGenre()
	{
		return fadeGenre;
	}

	// Flash Coroutine
	IEnumerator Flash()
	{
		while (true)
		{
			if (GetFadeGenre())
			{
				flashObjectName.GetComponent<Image>().enabled = !flashObjectName.GetComponent<Image>().enabled;
			}
			else
			{
				flashObjectName.GetComponent<Text>().enabled = !flashObjectName.GetComponent<Text>().enabled;
			}
			yield return new WaitForSeconds(flashInterval);
		}
	}

	public void StopFlash(bool flg = false)
	{
		flashObjectName.GetComponent<Image>().enabled = flg;
		StopCoroutine("Flash");
	}

	// Fade Flag
	public bool FadeJudge()
	{
		return fadeFlg;
	}
}
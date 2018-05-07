using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeScript : MonoBehaviour 
{
	private Color fadeColor;
	public float speed;
	public float interval;
	public float flashInterval;

	public float minAlpha;
	private bool alphaFlg;

	// Use this for initialization
	void Start () 
	{
		alphaFlg = true;
		fadeColor = gameObject.GetComponent<Image>().color;
		StartCoroutine("Fade");
		
	}
	IEnumerator Fade()
	{
		while (true)
		{
			if ((fadeColor.a > minAlpha) && (alphaFlg))
			{
				fadeColor.a -= speed;
				gameObject.GetComponent<Image>().color = fadeColor;

			}
			else if(fadeColor.a <= 1.0f)
			{
				alphaFlg = false;
				fadeColor.a += speed;
				gameObject.GetComponent<Image>().color = fadeColor;
			}
			else
			{
				alphaFlg = true;
			}

			fadeColor = gameObject.GetComponent<Image>().color;
			yield return new WaitForSeconds(interval);
		}
	}
	public IEnumerator FlashImage()
	{
		StopCoroutine("Fade");
		while (true)
		{
			gameObject.GetComponent<Image>().enabled = !gameObject.GetComponent<Image>().enabled;
			yield return new WaitForSeconds(flashInterval);
		}
	}
}

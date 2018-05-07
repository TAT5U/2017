using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CloseScript : MonoBehaviour 
{
	public ClickManager clickManager_;

	[SerializeField]private SoundScript ui_;

	public void Click()
	{
		clickManager_.CountInitialize();

		ui_.SoundPlay(4);

		transform.parent.gameObject.SetActive(false);
	}
}

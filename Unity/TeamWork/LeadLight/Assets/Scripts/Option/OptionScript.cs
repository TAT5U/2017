using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OptionScript : MonoBehaviour
{
    public Canvas canvas;
    public ClickManager clickManager_;

	[SerializeField]private SoundScript ui_;

    public void Click()
    {
        if (clickManager_.IsClickOK())
        {
			ui_.SoundPlay(3);
            GameObject optionObject = canvas.gameObject;
            foreach (Transform child in optionObject.transform)
            {
				if (child.name == "Option")
				{
					child.gameObject.SetActive(true);
				}
			}
        }
    }
}

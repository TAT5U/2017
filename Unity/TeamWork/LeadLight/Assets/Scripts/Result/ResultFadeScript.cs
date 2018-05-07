using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultFadeScript : MonoBehaviour
{
    public Avater player;

    // Update is called once per frame
    void Update()
    {
        if (!player.GetPlayGameFlg())
        {
            foreach (Transform child in transform)
            {
                child.gameObject.SetActive(true);
            }
            player.SetPlayGameFlg(true);
        }
    }

    public void ClickOption()
    {
        gameObject.SetActive(false);
    }

    public void CloseOption()
    {
        gameObject.SetActive(true);
    }
}

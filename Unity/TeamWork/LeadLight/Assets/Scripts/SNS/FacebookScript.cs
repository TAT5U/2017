using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FacebookScript : APILevelManager
{

    private Vector2 size;
    private Vector2 objSize;

    public ClickManager clickManager_;

    private void Start()
    {
        if (Application.platform == RuntimePlatform.Android)
        {
            base.APIJudge();

        }
    }

    public void Click()
    {
        if (clickManager_.IsClickOK())
        {
            StartCoroutine("CaptureResult");
        }
    }

    private IEnumerator CaptureResult()
    {
        string imagePath = Application.persistentDataPath + "/scoreScreenShot.png";

        // 画面をキャプチャ
        ScreenCapture.CaptureScreenshot("scoreScreenShot.png");

        // 1秒ディレイ
        // フレームだとキャプチャする前になってしまう
        yield return new WaitForSeconds(1.0f);

        if (Application.platform == RuntimePlatform.IPhonePlayer)
        {
            // フェイスブックの投稿画面呼び出し
            Binding.FacebookSend(imagePath);
        }
        else if (Application.platform == RuntimePlatform.Android)
        {
            using (AndroidJavaClass jclass = new AndroidJavaClass("com.hts.tat5u.tweetcodelibrary.TweetCode"))
            {
                jclass.CallStatic("FacebookShare", imagePath);
            }
        }

        clickManager_.CountInitialize();
    }
}

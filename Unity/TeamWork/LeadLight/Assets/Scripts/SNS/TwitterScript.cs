using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class TwitterScript : APILevelManager
{

    private Vector2 size;
    private Vector2 objSize;
    public ConfigScript config;

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
            // ツイートのスクリプト呼び出し
            Binding.Tweet("My Score!!", imagePath);
        }
        else if (Application.platform == RuntimePlatform.Android)
        {
            using (AndroidJavaClass jclass = new AndroidJavaClass("com.hts.tat5u.tweetcodelibrary.TweetCode"))
            {
                jclass.CallStatic("TweetShare", "My Score!!", imagePath);
            }
        }

        clickManager_.CountInitialize();
    }
}

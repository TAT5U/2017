using UnityEngine;
using UnityEngine.Assertions;
using UnityEngine.SceneManagement;

public class FadeManager : MonoBehaviour 
{
	[SerializeField]private bool isMultiple_ = false;
	[SerializeField, SceneName]private string[] sceneName_ = new string[1];
	[SerializeField, Range(0.0f, 0.10f)]private float fadeOutSpeed_ = 0.020f;
	[SerializeField, Range(0.0f, 0.10f)]private float fadeInSpeed_  = 0.040f;
	[SerializeField]private Color fadeColor_ = Color.black;

	[System.NonSerialized]public bool isFadeOn_ = false;
	private int sceneNumber_ = 0;

	private void OnValidate()
	{
		if (isMultiple_) return;
		System.Array.Resize(ref sceneName_, 1);
	}

	private void Awake()
	{
		fadeColor_.a = 0.0f;
		DontDestroyOnLoad(gameObject);
	}

	public void OnGUI()
	{
		GUI.color = fadeColor_;
		GUI.DrawTexture(new Rect(0.0f, 0.0f, Screen.width, Screen.height), Texture2D.whiteTexture);
	}

	public void FadeStart(int sceneNumber = 0)
	{
		ExceptionDetection(sceneNumber);
		sceneNumber_ = sceneNumber;
		FadeOut();
	}

	private void FadeOut()
	{
		if (fadeColor_.a >= 1.0f)
		{
			SceneChange();
			return;
		}

		fadeColor_.a += fadeOutSpeed_;
		Invoke("FadeOut", fadeOutSpeed_);
	}

	private void SceneChange()
	{
		if (!isFadeOn_)
		{
			SceneManager.LoadScene(sceneName_[sceneNumber_]);
		}
		FadeIn();
	}

	private void FadeIn()
	{
		if (fadeColor_.a <= 0.0f)
		{
			FadeManagerDestroy();
			return;
		}
		fadeColor_.a -= fadeInSpeed_;
		Invoke("FadeIn", fadeInSpeed_);
	}

	private void FadeManagerDestroy()
	{
		if (isFadeOn_) return;
		Destroy(gameObject);
	}


	private void ExceptionDetection(int sceneNumber)
	{
		if (isFadeOn_) return;
		bool isOutOfRange = (sceneName_.Length - 1) < sceneNumber;
		Assert.IsFalse(isOutOfRange && !isMultiple_, 
		               "致命的なエラー : 単体モードです。");
		
		Assert.IsFalse(isOutOfRange && isMultiple_, 
		               "致命的なエラー : 登録されているSceneの数が少ないです。");
	}
}

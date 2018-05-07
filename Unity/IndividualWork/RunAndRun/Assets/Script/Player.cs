using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour 
{
	[SerializeField]private float jumpPower_;

	private int jumpCount_ = 0;
	public Camera mainCamera_;
	private float offsetX_;
	private bool isRun_ = true;

	void Awake()
	{
		offsetX_ = mainCamera_.WorldToScreenPoint(transform.position).x - mainCamera_.transform.position.x;
	}

	// Update is called once per frame
	void Update () 
	{
		if (Input.GetKey(KeyCode.Space) && IsJumpOK())
		{
			GetComponent<Rigidbody2D>().AddForce(new Vector3(0.0f, jumpPower_ * 1500, 0.0f) * Time.deltaTime);
		}

		if (transform.position.x + offsetX_ / 50 < mainCamera_.transform.position.x)
		{
			SceneManager.LoadScene(2);
		}
	}

	private bool IsJumpOK()
	{
		if (jumpCount_ <= 0)
		{
			jumpCount_++;
			return true;
		}
		return false;
	}

	private void OnCollisionEnter2D(Collision2D col)
	{
		if (col.gameObject.tag == "Ground")
		{
			jumpCount_ = 0;
		}
		else if (col.gameObject.tag == "Stone")
		{
			isRun_ = false;
		}
	}

	private void OnCollisionExit2D(Collision2D col)
	{
		if (col.gameObject.tag == "Stone")
		{
			isRun_ = true;
		}
	}

	public bool IsRunning()
	{
		return isRun_;
	}
}

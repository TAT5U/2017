#import<Social/Social.h>
#import"UnityAppController.h"

// Cのコードに変換
extern "C"
{
    // 関数を使えるように宣言
    void TweetShare(const char *tweetText, const char *tweetImagePath);
    void FacebookShare(const char *sendImagePath);
    
    // Twitter関数
    void TweetShare(const char *tweetText, const char *tweetImagePath)
    {
        // ツイートするための変数
        SLComposeViewController *tweet =[SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
        
        // テキストをセット
        [tweet setInitialText:[NSString stringWithUTF8String:tweetText]];
        
        // 画像のパスを一度設定
        UIImage *image = [UIImage imageWithContentsOfFile:[NSString stringWithUTF8String:tweetImagePath]];
        
        // 画像をセット
        [tweet addImage:image];
        
        // Unityで使えるようにする変数
        UnityAppController *unityController = [[UIApplication sharedApplication]delegate];
        
        // 送る
        [unityController.rootViewController presentViewController:tweet animated:YES completion:nil];
    }
    
    // Facebook関数
    void FacebookShare(const char *sendImagePath)
    {
        // ツイートするための変数
        SLComposeViewController *sendData =[SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
        
        // 画像のパスを一度設定
        UIImage *image = [UIImage imageWithContentsOfFile:[NSString stringWithUTF8String:sendImagePath]];
        
        // 画像をセット
        [sendData addImage:image];
        
        // Unityで使えるようにする変数
        UnityAppController *unityController = [[UIApplication sharedApplication]delegate];
        
        // 送る
        [unityController.rootViewController presentViewController:sendData animated:YES completion:nil];
    }
}

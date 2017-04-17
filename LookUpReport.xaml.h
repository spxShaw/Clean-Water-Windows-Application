//
// LookUpReport.xaml.h
// Declaration of the LookUpReport class
//

#pragma once

#include "LookUpReport.g.h"

namespace Clean_Water_Project
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class LookUpReport sealed
	{
	public:
		LookUpReport();
	private:
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void lookUpReport_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}

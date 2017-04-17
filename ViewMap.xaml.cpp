//
// ViewMap.xaml.cpp
// Implementation of the ViewMap class
//

#include "pch.h"
#include "ViewMap.xaml.h"

using namespace Clean_Water_Project;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Controls::Maps;
using namespace Windows::Devices::Geolocation;

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

ViewMap::ViewMap()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &ViewMap::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &ViewMap::SaveState);
}

DependencyProperty^ ViewMap::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(ViewMap::typeid), nullptr);

/// <summary>
/// Used as a trivial view model.
/// </summary>
IObservableMap<String^, Object^>^ ViewMap::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ ViewMap::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(ViewMap::typeid), nullptr);

/// <summary>
/// Gets an implementation of <see cref="NavigationHelper"/> designed to be
/// used as a trivial view model.
/// </summary>
Common::NavigationHelper^ ViewMap::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support

/// The methods provided in this section are simply used to allow
/// NavigationHelper to respond to the page's navigation methods.
/// 
/// Page specific logic should be placed in event handlers for the  
/// <see cref="NavigationHelper::LoadState"/>
/// and <see cref="NavigationHelper::SaveState"/>.
/// The navigation parameter is available in the LoadState method 
/// in addition to page state preserved during an earlier session.

void ViewMap::OnNavigatedTo(NavigationEventArgs^ e)
{
	
	BasicGeoposition Atlanta = { 33.7, -84.3 };

	auto gp = ref new Geopoint(Atlanta);

	this->MapControl1->Center = gp;
	this->MapControl1->ZoomLevel = 8;
	this->MapControl1->LandmarksVisible = true;


	//Initialization data


	AddMapIcon(32, -85);
	AddMapIcon(32, -83);
	AddMapIcon(32, -83);
	AddMapIcon(34, -83);
}

void ViewMap::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion

/// <summary>
/// Populates the page with content passed during navigation. Any saved state is also
/// provided when recreating a page from a prior session.
/// </summary>
/// <param name="sender">
/// The source of the event; typically <see cref="NavigationHelper"/>
/// </param>
/// <param name="e">Event data that provides both the navigation parameter passed to
/// <see cref="Frame::Navigate(Type, Object)"/> when this page was initially requested and
/// a dictionary of state preserved by this page during an earlier
/// session. The state will be null the first time a page is visited.</param>
void ViewMap::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Unused parameter
	(void) e;	// Unused parameter
}

/// <summary>
/// Preserves state associated with this page in case the application is suspended or the
/// page is discarded from the navigation cache.  Values must conform to the serialization
/// requirements of <see cref="SuspensionManager::SessionState"/>.
/// </summary>
/// <param name="sender">The source of the event; typically <see cref="NavigationHelper"/></param>
/// <param name="e">Event data that provides an empty dictionary to be populated with
/// serializable state.</param>
void ViewMap::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Unused parameter
	(void) e; // Unused parameter
}

void ViewMap::AddMapIcon(int lattitude, int longitude)
{
	BasicGeoposition location = { lattitude, longitude};
	auto gp = ref new Geopoint(location);

	auto mapIcon1 = ref new MapIcon();
	//mapIcon1->Title = "title"; //Correct this later
	mapIcon1->Location = gp;
	mapIcon1->NormalizedAnchorPoint = Point(0.5, 1.0);
	mapIcon1->ZIndex = 2;
	this->MapControl1->MapElements->Append(mapIcon1);
}

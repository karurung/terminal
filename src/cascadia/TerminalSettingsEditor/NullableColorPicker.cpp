// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "NullableColorPicker.h"
#include "NullableColorPicker.g.cpp"

#include <LibraryResources.h>

using namespace winrt;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Navigation;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt
{
    namespace MUX = Microsoft::UI::Xaml;
    namespace WUX = Windows::UI::Xaml;
}

namespace winrt::Microsoft::Terminal::Settings::Editor::implementation
{
    DependencyProperty NullableColorPicker::_ColorSchemeVMProperty{ nullptr };
    DependencyProperty NullableColorPicker::_CurrentColorProperty{ nullptr };

    NullableColorPicker::NullableColorPicker()
    {
        _InitializeProperties();
        InitializeComponent();
    }

    void NullableColorPicker::_InitializeProperties()
    {
        // Initialize any dependency properties here.
        // This performs a lazy load on these properties, instead of
        // initializing them when the DLL loads.
        if (!_ColorSchemeVMProperty)
        {
            _ColorSchemeVMProperty =
                DependencyProperty::Register(
                    L"ColorSchemeVM",
                    xaml_typename<Editor::ColorSchemeViewModel>(),
                    xaml_typename<Editor::NullableColorPicker>(),
                    PropertyMetadata{ nullptr });
        }
        if (!_CurrentColorProperty)
        {
            _CurrentColorProperty =
                DependencyProperty::Register(
                    L"CurrentColor",
                    xaml_typename<Windows::Foundation::IReference<Microsoft::Terminal::Core::Color>>(),
                    xaml_typename<Editor::NullableColorPicker>(),
                    PropertyMetadata{ nullptr });
        }
    }

    void NullableColorPicker::ColorChip_Clicked(const IInspectable& sender, const RoutedEventArgs& /*args*/)
    {
        const auto& btn = sender.as<Windows::UI::Xaml::Controls::Primitives::ToggleButton>();
        const auto& colorEntry = btn.DataContext().as<Editor::ColorTableEntry>();
        const auto& colorEntryColor = colorEntry.Color();
        const Microsoft::Terminal::Core::Color terminalColor{ colorEntryColor.R, colorEntryColor.G, colorEntryColor.B, colorEntryColor.A };
        CurrentColor(terminalColor);
        btn.IsChecked(true);
    }

    void NullableColorPicker::MoreColors_Clicked(const IInspectable& /*sender*/, const RoutedEventArgs& /*args*/)
    {
    }
}
